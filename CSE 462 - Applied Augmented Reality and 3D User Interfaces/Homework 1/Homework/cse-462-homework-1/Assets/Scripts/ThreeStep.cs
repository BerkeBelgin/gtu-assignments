using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThreeStep : MonoBehaviour
{
    public GameObject label1;
    public GameObject label2;
    public GameObject label3;
    public GameObject label4;
    public GameObject label5;
    public GameObject label6;

    public GameObject button1;
    public GameObject button2;
    public GameObject button3;
    public GameObject button4;
    public GameObject button5;
    public GameObject button6;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.GetTouch(0).position);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                if (hit.collider.gameObject.GetInstanceID() == button1.GetInstanceID())
                {
                    label1.SetActive(true);
                    label2.SetActive(false);
                    label3.SetActive(false);
                    label4.SetActive(false);
                    label5.SetActive(false);
                    label6.SetActive(false);
                }
                else if (hit.collider.gameObject.GetInstanceID() == button2.GetInstanceID())
                {
                    label1.SetActive(false);
                    label2.SetActive(true);
                    label3.SetActive(false);
                    label4.SetActive(false);
                    label5.SetActive(false);
                    label6.SetActive(false);
                } else if (label1.activeSelf || label2.activeSelf) {
                    if (hit.collider.gameObject.GetInstanceID() == button3.GetInstanceID())
                    {
                        label3.SetActive(true);
                        label4.SetActive(false);
                        label5.SetActive(false);
                        label6.SetActive(false);
                    }
                    else if (hit.collider.gameObject.GetInstanceID() == button4.GetInstanceID())
                    {
                        label3.SetActive(false);
                        label4.SetActive(true);
                        label5.SetActive(false);
                        label6.SetActive(false);
                    }
                    else if (label3.activeSelf || label4.activeSelf)
                    {
                        if (hit.collider.gameObject.GetInstanceID() == button5.GetInstanceID())
                        {
                            label5.SetActive(true);
                            label6.SetActive(false);
                        }
                        else if (hit.collider.gameObject.GetInstanceID() == button6.GetInstanceID())
                        {
                            label5.SetActive(false);
                            label6.SetActive(true);
                        }
                    }
                }
            }
        }
    }
}
